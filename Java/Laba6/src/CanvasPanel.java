// Mamaev 36


import javax.swing.*;
import java.awt.*;

public class CanvasPanel extends JPanel {
    private double sin30 = Math.sin(Math.PI/6), cos30 = Math.cos(Math.PI/6);
    private int x0 = 400, y0 = 400;
    private int a = 100;
    boolean oct = false;

    public void setA(int r){
        a = r;
        repaint();
    }

    public void setOct(boolean doOct){
        oct = doOct;
        repaint();
    }

    protected void paintComponent(Graphics g2) {
        Graphics2D g = (Graphics2D) g2;
        super.paintComponent(g);

        g.setColor(Color.red);
        g.setStroke(new BasicStroke(1.0f));

        g.drawLine(x0, y0, x0, y0 - a);
        g.drawLine(x0, y0, x0 + (int)(cos30*a), y0 + (int)(sin30*a));
        g.drawLine(x0, y0, x0 - (int)(cos30*a), y0 + (int)(sin30*a));

        g.setStroke(new BasicStroke(2.0f));

        g.drawLine(x0, y0, x0, y0 + a);
        g.drawLine(x0, y0, x0 + (int)(cos30*a), y0 - (int)(sin30*a));
        g.drawLine(x0, y0, x0 - (int)(cos30*a), y0 - (int)(sin30*a));
        g.drawLine(x0, y0 + a, x0 + (int)(cos30*a), y0 + a - (int)(sin30*a));
        g.drawLine(x0, y0 + a, x0 - (int)(cos30*a), y0 + a - (int)(sin30*a));

        g.drawLine(x0, y0 - a, x0 + (int)(cos30*a), y0 - a + (int)(sin30*a));
        g.drawLine(x0, y0 - a, x0 - (int)(cos30*a), y0 - a + (int)(sin30*a));

        g.drawLine(x0 + (int)(cos30*a), y0 - (int)(sin30*a), x0 + (int)(cos30*a), y0 - (int)(sin30*a) + a);
        g.drawLine(x0 - (int)(cos30*a), y0 - (int)(sin30*a), x0 - (int)(cos30*a), y0 - (int)(sin30*a) + a);

        if(oct){
            g.setColor(Color.green);
            g.setStroke(new BasicStroke(1.5f));
            g.drawLine(x0, y0 - a/2, x0 - (int)(a*cos30/2), y0 - (int)(a*sin30/2));
            g.drawLine(x0, y0 - a/2, x0 - (int)(a*cos30/2), y0 + (int)(a*sin30/2));
            g.drawLine(x0, y0 - a/2, x0 + (int)(a*cos30/2), y0 - (int)(a*sin30/2));
            g.drawLine(x0, y0 - a/2, x0 + (int)(a*cos30/2), y0 + (int)(a*sin30/2));

            g.drawLine(x0 - (int)(a*cos30/2), y0 - (int)(a*sin30/2),
                    x0 - (int)(a*cos30/2), y0 + (int)(a*sin30/2));
            g.drawLine(x0 - (int)(a*cos30/2), y0 - (int)(a*sin30/2),
                    x0 + (int)(a*cos30/2), y0 - (int)(a*sin30/2));
            g.drawLine(x0 + (int)(a*cos30/2), y0 + (int)(a*sin30/2),
                    x0 - (int)(a*cos30/2), y0 + (int)(a*sin30/2));
            g.drawLine(x0 + (int)(a*cos30/2), y0 + (int)(a*sin30/2),
                    x0 + (int)(a*cos30/2), y0 - (int)(a*sin30/2));

            g.drawLine(x0, y0 + a/2, x0 - (int)(a*cos30/2), y0 - (int)(a*sin30/2));
            g.drawLine(x0, y0 + a/2, x0 - (int)(a*cos30/2), y0 + (int)(a*sin30/2));
            g.drawLine(x0, y0 + a/2, x0 + (int)(a*cos30/2), y0 - (int)(a*sin30/2));
            g.drawLine(x0, y0 + a/2, x0 + (int)(a*cos30/2), y0 + (int)(a*sin30/2));

        }

    }
}
