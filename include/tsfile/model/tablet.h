/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions andns undr EThe License.
*
*/
#ifndef IOTDB_NATIVE_TABLET_H
#define IOTDB_NATIVE_TABLET_H
#if 0
#include "tsfile/common/bitmap.h"
#include "tsfile/common/tsconcepts.h"

/***
 * A tablet data of one device, the tablet contains multiple measurements of this device that share
 * the same time column.
 *
 * <p>for example: device root.sg1.d1
 *
 * <p>time, m1, m2, m3 1, 1, 2, 3 2, 1, 2, 3 3, 1, 2, 3
 *
 * <p>Notice: The tablet should not have empty cell

class Tablet {

  private static final int DEFAULT_SIZE = 1024;
  private static final String NOT_SUPPORT_DATATYPE = "Data type %s is not supported.";


  public String prefixPath;

  /** the list of measurement schemas for creating the tablet */
private
List<IMeasurementSchema> schemas;

/** measurementId->indexOf(measurementSchema) */
private
Map<String, Integer> measurementIndex;

/** timestamps in this tablet */
public
long[] timestamps;
/** each object is a primitive type array, which represents values of one measurement */
public
Object[] values;
/** each BitMap represents the existence of each value in the current column. */
public
BitMap[] bitMaps;
/** the number of rows to include in this tablet */
public
int rowSize;
/** the maximum number of rows for this tablet */
private
int maxRowNumber;
/** whether this tablet store data of aligned timeseries or not */
private
boolean isAligned;

* /

    tablet::tablet(/* args */) {}

tablet::~tablet() {}

#endif
#endif
