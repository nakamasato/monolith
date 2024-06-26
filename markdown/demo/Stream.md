# Stream training tutorial
> This tutorial depends on the batching training tutorial. Please read it first if you haven't.

Monolith supports reading input data from Kafka stream. To add stream training support to your model, simply change the `input_fn` and read data from a KafkaDataset.

## Kafka setup

1. Install Java from https://www.java.com/en/download/
    ```
    java -version
    java version "1.8.0_411"
    Java(TM) SE Runtime Environment (build 1.8.0_411-b09)
    Java HotSpot(TM) 64-Bit Server VM (build 25.411-b09, mixed mode)
    ```
1. `cd ./markdown/demo/kafka_utils`
1. Download Kafka from https://kafka.apache.org/downloads#2.8.1
    ```
    curl -fLO "https://archive.apache.org/dist/kafka/2.8.1/kafka_2.13-2.8.1.tgz"
    tar -xvzf kafka_2.13-2.8.1.tgz
    ```
1. Set KAFKA_PATH e.g. `export KAFKA_PATH=$HOME/Downloads/kafka_2.13-2.8.1`
1. `./start_broker.sh`
1. Check kafka: `nc -vz localhost 9092`, and zookeeper: `nc -vz localhost 2181`
1. Create `movie-train` topic `./add_data_topics.sh`


## Kafka producer

Source code: [kafka_producer.py](./kafka_producer.py)

Let's create a kafka producer for our movie-lens dataset. Kafka requires serializing everything to bytes, so we convert each data item in the dataset to String by putting them into the standard Tensorflow Example protobuf.

```python
def serialize_one(data):
  # serialize an training instance to string
  return tf.train.Example(features=tf.train.Features(
    feature={
      'mov': tf.train.Feature(int64_list=tf.train.Int64List(value=data['mov'])),
      'uid': tf.train.Feature(int64_list=tf.train.Int64List(value=data['uid'])),
      'label': tf.train.Feature(float_list=tf.train.FloatList(value=data['label']))
    }
  )).SerializeToString()
```

Then, we create a KafkaProducer, iterate over the dataset, serializing each item and write it to the desired kafka topic.

```python
if __name__ == "__main__":
  ds = get_preprocessed_dataset()
  producer = KafkaProducer(bootstrap_servers=['127.0.0.1:9092'])
  for count, val in tqdm(enumerate(ds), total=len(ds)):
    # note: we omit error callback here for performance
    producer.send(
      "movie-train", key=str(count).encode('utf-8'), value=serialize_one(val), headers=[])
  producer.flush()
```

Run:

```
bazel run //markdown/demo:kafka_producer
```

Error:

```
external/boringssl/err_data.c:45:1: error: static assertion failed due to requirement '40 == 24': library value changed
OPENSSL_STATIC_ASSERT(ERR_LIB_UI == 24, "library value changed");
^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
external/boringssl/src/include/openssl/type_check.h:75:42: note: expanded from macro 'OPENSSL_STATIC_ASSERT'
#define OPENSSL_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
                                         ^              ~~~~
external/boringssl/err_data.c:46:1: error: static assertion failed due to requirement '41 == 25': library value changed
OPENSSL_STATIC_ASSERT(ERR_LIB_COMP == 25, "library value changed");
^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
external/boringssl/src/include/openssl/type_check.h:75:42: note: expanded from macro 'OPENSSL_STATIC_ASSERT'
```

## Kafka consumer in the input_fn

Source code: [kafka_receiver.py](./kafka_receiver.py) and [demo_model.py](./demo_model.py)

Since the kafka stream contains serialized `tf.train.Example`, we can use `tf.io.parse_example` to parse multiple of them at once.

```python
def decode_example(v):
    x = tf.io.parse_example(v, raw_feature_desc)
    return to_ragged(x)
```

In the `input_fn`, we use the Monolith's utility function to create a kafka dataset, and use the function above the decode. The parameter `poll_batch_size` determines the how many serialized `Example` we should batch before sending them to `decode_example`. It effectively means the training batch size.

```python
def input_fn(self, mode):
  dataset = create_plain_kafka_dataset(topics=["movie-train"],
      group_id="cgonline",
      servers="127.0.0.1:9092",
      stream_timeout=10000,
      poll_batch_size=16,
      configuration=[
        "session.timeout.ms=7000",
        "max.poll.interval.ms=8000"
      ],
  )
  return dataset.map(lambda x: decode_example(x.message))
```
