package iotdb.interop.testcommand;

import java.io.FileOutputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.nio.file.Path;
import java.nio.file.Paths;

public class DataSerializer {
    public static <T> void Save(String fileName, String directory, T header) {
        Path filePath = Paths.get(directory, fileName);
        try {
            FileOutputStream fos = new FileOutputStream(filePath.toString());
            // unluckly get PageHeader and ChunkHeader doesnt abstract serializer
            Method method = header.getClass().getMethod("serializeTo", OutputStream.class);
            method.invoke(header, fos);
        } catch (Exception ex) {
            System.out.println("Exception writing serialized data"  + ex.getMessage());
        }
    }
}
