// Mamaev 36

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class PictureForm {
    private JPanel mainPanel;
    private JSpinner aSpinner;
    private CanvasPanel canvasPanel;
    private JCheckBox checkBox;

    PictureForm(){
        aSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int radius = (int) aSpinner.getValue();
                canvasPanel.setA(radius);
            }
        });
        aSpinner.setValue(100);

        checkBox.addChangeListener(new ChangeListener(){
            @Override
            public void stateChanged(ChangeEvent e){
                canvasPanel.setOct(checkBox.isSelected());
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Cube");
        frame.setContentPane(new PictureForm().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}
