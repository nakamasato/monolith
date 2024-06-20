# Monolith

## What is it?

[Monolith](https://arxiv.org/abs/2209.07663) is a deep learning framework for large scale recommendation modeling. It introduces two important features which are crucial for advanced recommendation system:
* collisionless embedding tables guarantees unique represeantion for different id features
* real time training captures the latest hotspots and help users to discover new intersts rapidly

Monolith is built on the top of TensorFlow and supports batch/real-time training and serving.


## Quick start

### Prerequisite

- Python 3.8.6
- Bazel Version 4.0.0
- Java: 1.8.0
- Kafka: 2.13-2.8.1

### Python setup

```
asdf local python 3.8.6
python -m venv .venv
. .venv/bin/activate
pip install -r requirements.txt
```

### Bazel setup

```
export BAZEL_VERSION=4.0.0
curl -fLO "https://github.com/bazelbuild/bazel/releases/download/$BAZEL_VERSION/bazel-$BAZEL_VERSION-installer-darwin-x86_64.sh"
chmod +x "bazel-$BAZEL_VERSION-installer-darwin-x86_64.sh"
./bazel-$BAZEL_VERSION-installer-darwin-x86_64.sh --user
export PATH="$PATH:$HOME/bin"
```

### Examples

1. **native_training:demo**: `bazel run //monolith/native_training:demo --output_filter=IGNORE_LOGS` ⚠️ (segmentation fault)
1. [**batch**](markdown/demo/Batch.md): `bazel run //markdown/demo:demo_local_runner -- --training_type=batch` ⚠️ (segmentation fault)
1. [**streaming**](markdown/demo/Stream.md): ❌ `static assertion failed due to requirement`
1. **Kubernetes**:
    1. [EKS](markdown/demo/AWS-EKS.md): todo
    1. [GKE](markdown/demo/GCP-GKE.md): todo

### Demo and tutorials

There are a tutorial in [markdown/demo](markdown/demo) on how to run distributed async training, and few guides on how to use the `MonolithModel` API [here](markdown).

## Tips

When you encounter a problem and want to clean up the bazel cache, you can use the following command:

```
bazel clean --expunge
```
