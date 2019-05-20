package thermopic;

import com.fazecast.jSerialComm.SerialPort;

import java.util.ArrayList;
import java.util.List;

public class Controller {
    public static Controller instance;
    private final Model model;
    private final View view;

    public Controller(Model model, View view) {
        this.view = view;
        this.model = model;
        instance = this;
        model.listener = value -> {
            //view.setTemperature();
        };
    }

    public void init() {
        view.start();
    }

    public void setSerial(String selectedItem) {
        model.setSerial(selectedItem);
    }

    public void detect() {
        SerialPort[] commPorts = Model.instance.getCommPorts();
        List<String> serialNames = new ArrayList<>();
        for (SerialPort commPort : commPorts) {
            String name = commPort.getSystemPortName();
            System.out.println(name);
            serialNames.add(name);
        }
        view.setSerials(serialNames);
    }


    public void exit() {
        System.exit(0);
    }
}
