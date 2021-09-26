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
package iotdb.interop;
import iotdb.interop.testcommand.ChunkHeaderTestCommand;
import iotdb.interop.testcommand.ITestCommand;
import iotdb.interop.testcommand.PageHeaderTestCommand;
import java.io.File;
import java.util.ArrayList;

public class App {
    private static ArrayList<ITestCommand> commands = new ArrayList<>();
    public static void main(String[] args) {
        if (args.length == 1) {
            var path = args[0];
            var file = new File(path);
            if (file.isDirectory()) {
                commands.add(new ChunkHeaderTestCommand());
                commands.add(new PageHeaderTestCommand());
            }
            for (ITestCommand c : commands) {
                c.executeSerialization(path);
            }
            return;
        }
        throw new IllegalArgumentException("Tests need a valid destination path");
    }
}
