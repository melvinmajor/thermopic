package thermopic;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

public class Model {
    public static Model instance;
    private SerialPort comPort;
    public Listener listener;

    public Model() {
        instance = this;
    }

    public void setSerial(String selectedItem) {
        if (this.comPort != null) {
            this.comPort.closePort();
            this.comPort = null;
        }

        SerialPort[] commPorts = Model.instance.getCommPorts();
        for (SerialPort commPort : commPorts) {
            String name = commPort.getSystemPortName();
            if (name.equals(selectedItem)) {
                this.comPort = commPort;
                break;
            }
        }
        if (this.comPort == null) return;
        this.comPort.openPort();
        comPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 100, 0);

        comPort.addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
            }

            @Override
            public void serialEvent(SerialPortEvent event) {
                if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE)
                    return;
                byte[] newData = new byte[comPort.bytesAvailable()];
                int numRead = comPort.readBytes(newData, newData.length);
                Model.this.listener.onRead(newData);
            }
        });

    }

    public void write(byte[] value) {
        if (this.comPort == null) {
            return;
        }
        this.comPort.writeBytes(value, 8);
    }

    public SerialPort[] getCommPorts() {
        return SerialPort.getCommPorts();
    }
}
