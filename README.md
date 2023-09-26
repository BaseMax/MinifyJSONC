# JSON Minification Tool

A simple C program to minify JSON files by removing whitespace and comments.

## Introduction

JSON Minification Tool is a command-line utility that takes a JSON file as input, removes unnecessary whitespace and comments, and outputs a minified JSON file. Minified JSON is useful for reducing file size and improving performance when transmitting JSON data over the internet.

## Features

- Minify JSON by removing:
  - Whitespace characters (spaces, tabs, newlines, and carriage returns).
  - Single-line (`//`) and multiline (`/* ... */`) comments.
- Easy-to-use command-line interface.
- Supports both single-line and multiline comments within JSON data.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- Make (optional, for building)
- Git (optional, for cloning the repository)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/BaseMax/MinifyJSONC
   ```

    Or download the ZIP file and extract it.

2. Build the JSON minification tool (optional):
   ```console
   make
   ```

   This step is optional, as you can also compile the C code using your preferred C compiler.

  ### Usage

  To minify a JSON file, use the following command:
  ```console
  ./minify_json input.json output.json
  ```

  - Replace input.json with the path to your input JSON file.
  - Replace output.json with the desired name for the minified output JSON file.

Copyright 2023, Max Base
