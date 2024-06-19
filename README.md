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

### Python setup

```
asdf local python 3.8.6
python -m venv .venv
. .venv/bin/activate
pip install -U numpy wheel packaging requests opt_einsum
pip install -U keras_preprocessing --no-deps
```

### Bazel setup

```

```

### Build from source

Demo

```bash
bazel run //monolith/native_training:demo --output_filter=IGNORE_LOGS
```

### Demo and tutorials

There are a tutorial in [markdown/demo](markdown/demo) on how to run distributed async training, and few guides on how to use the `MonolithModel` API [here](markdown).
