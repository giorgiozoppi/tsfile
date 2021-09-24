# Apache IoTDB TsFile Native.
![Build Status](https://app.travis-ci.com/giorgiozoppi/tsfile.svg?branch=dev)

## Welcome!
Apache IoTDB TsFile Native is library for reading/storing Apache IOTDB TsFile. TsFile is a columnar storage file format designed for time series data, which supports efficient compression and query. It is easy to integrate TsFile into your IoT big data processing frameworks.

## Motivation

The target of TsFile project is to support: high ingestion rate up to tens of million data points per second and rare updates only for the correction of low quality data; compact data packaging and deep compression for long-live historical data; traditional sequential and conditional query, complex exploratory query, signal processing, data mining and machine learning. The goal of this project is to provide tsfile for embedded applications where resource consumption is improtant.

## Status

We've just stated so for the moment is just an exercise in C++ 20 but we plan to work on it deeply in the next weeks.

## Features
The features of TsFile is as follow:

- Write
  - Fast data import
  - Efficiently compression schemas, diverse data encoding types
- Read
  - Efficiently query
  - Time-sorted query data set


