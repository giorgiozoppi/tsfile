/**
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/
package iotdb.interop.testcommand;
import org.apache.iotdb.tsfile.file.header.PageHeader;
import org.apache.iotdb.tsfile.file.metadata.enums.TSDataType;
import org.apache.iotdb.tsfile.file.metadata.statistics.Statistics;

import java.io.FileOutputStream;
import java.lang.reflect.Method;
import java.nio.file.Paths;

public class PageHeaderTestCommand implements ITestCommand {
    public static final int UNCOMPRESSED_SIZE = 123456;
    public static final int COMPRESSED_SIZE = 100000;
    public static final int NUM_OF_VALUES = 10000;
    public static final long MAX_TIMESTAMP = 523372036854775806L;
    public static final long MIN_TIMESTAMP = 423372036854775806L;
    public static final TSDataType DATA_TYPE = TSDataType.INT64;
    private DataSerializer serializer = new DataSerializer();
    @Override
    public void executeSerialization(String path) {
        Statistics<?> statistics = Statistics.getStatsByType(DATA_TYPE);
        statistics.setEmpty(false);
        PageHeader pageHeader = new PageHeader(UNCOMPRESSED_SIZE, COMPRESSED_SIZE, NUM_OF_VALUES, statistics, MAX_TIMESTAMP, MIN_TIMESTAMP);
        serializer.Save("pageHeader.dat",path,pageHeader);
    }
}
