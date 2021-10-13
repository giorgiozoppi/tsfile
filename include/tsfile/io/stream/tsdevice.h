/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef IOTDB_NATIVE_TS_DEVICE_H
#define IOTDB_NATIVE_TS_DEVICE_H
#include "tsfile/common/common.h"

namespace tsfile {
template <typename T>
class TsDevice {
   public:
    enum class OpenMode {
        NotOpen = 0x0000,
        WriteOnly = 0x0001,
        ReadOnly = 0x0002,
        ReadWrite = 0x0001 | 0x0002,
        Append = 0x0004,
        Truncate = 0x0008
    };
    bool Open(TsDevice::OpenMode mode) { return static_cast<T&>(*this).Open(mode); }
    void Close() { return static_cast<T&>(*this).Close(); }

   private:
    TsDevice(){};
    friend T;
};
class TsFileDevice : public TsDevice<TsFileDevice> {};
class TsHDFSFileDevice : public TsDevice<TsFileDevice> {};

}  // namespace tsfile
#endif
