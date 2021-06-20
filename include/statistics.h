/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef IOTDB_NATIVE_STATISTICS_H
#define IOTDB_NATIVE_STATISTICS_H

#include <util/rwio.h>

namespace iotdb {
    namespace tsfile {
        namespace file {
            // see: https://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class

            template<typename Kind>
            class abstract_statistics {
            public:
                abstract_statistics(): _start_time(0), _end_time(0), _count(0) {}

                long get_start_time() const {
                    return _start_time;
                }

                void set_start_time(long start_time) {
                    _start_time = start_time;
                }

                void set_end_time(long end_time) {
                    _end_time = end_time;
                }

                void set_count(long count) {
                    _count = count;
                }

                long get_end_time() const {
                    return _end_time;
                }

                long get_count() const {
                    return _count;
                }

            protected:
                long _start_time;
                long _end_time;
                long _count;
            };
            class standard_statistics: public abstract_statistics<standard_statistics> {
            public:
                    standard_statistics(): abstract_statistics<standard_statistics>() {

                    }
            };
        }

    }
}
#endif //IOTDB_NATIVE_STATISTICS_H
