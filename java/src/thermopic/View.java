package thermopic;

import javax.swing.*;

import static javax.swing.JOptionPane.ERROR_MESSAGE;

public class View {
    public static View instance;

    private JFrame frame = new JFrame();
    private JPanel mainPanel;
    private JLabel label;
    private JLabel temperatureLabel;
    private JComboBox<String> serialComboBox;
    private JButton connectButton;
    private JButton detectButton;
    private JButton exitButton;
    private JTextField alertField;

    public View() {
        instance = this;

        exitButton.addActionListener(e -> Controller.instance.exit());

        detectButton.addActionListener(actionEvent -> Controller.instance.detect());

        connectButton.addActionListener(actionEvent -> {
            String selectedItem = (String) serialComboBox.getSelectedItem();
            if (selectedItem == null) {
                JOptionPane.showMessageDialog(null, "No serial port selected", "ERROR", ERROR_MESSAGE);
                return;
            }
            Controller.instance.setSerial(selectedItem);
        });
    }

    public void start() {
        frame.setContentPane(new View().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1380, 820);
        frame.setVisible(true);
    }

    public void setTemperature(String label) {
        temperatureLabel.setText(label);
    }

    public void setSerials(Iterable<String> entries) {
        SwingUtilities.invokeLater(() -> {
            serialComboBox.removeAllItems();
            for (String entry : entries) {
                serialComboBox.addItem(entry);
            }
        });
    }

}
