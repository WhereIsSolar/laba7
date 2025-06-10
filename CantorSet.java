import javax.swing.*;
import java.awt.*;
import java.util.Scanner;

public class CantorSet extends JFrame {

    private int maxDepth;
    private final int width = 800;
    private final int height = 600;

    public CantorSet(int maxDepth) {
        this.maxDepth = maxDepth;
        setTitle("Множество Кантора");
        setSize(width, height);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        getContentPane().setBackground(Color.BLACK);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setColor(Color.WHITE);
        drawCantorSet(g2d, 50, 50, 700, 0);
        System.out.println("Отрисовка завершена");
    }

    private void drawCantorSet(Graphics2D g, double x, double y, double length, int depth) {
        if (depth >= maxDepth) {
            System.out.println("Достигнута глубина: " + depth);
            return;
        }
        
        // Отрисовка текущего отрезка
        g.drawLine((int) x, (int) y, (int) (x + length), (int) y);
        System.out.printf("Отрисован отрезок: x=%.1f y=%.1f длина=%.1f уровень=%d%n",
                          x, y, length, depth);
        
        // Вычисление параметров для след. уровня
        double newLength = length / 3;
        double newY = y + 50;
        
        // Рекурсивный вызов для левой и правой третей
        drawCantorSet(g, x, newY, newLength, depth + 1);
        drawCantorSet(g, x + 2 * newLength, newY, newLength, depth + 1);
    }

    public static void main(String[] args) {
        System.out.println("Запуск программы для построения множества Кантора");
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите макс. глубину рекурсии: ");
        int depth = scanner.nextInt();
        scanner.close();

        SwingUtilities.invokeLater(() -> {
            CantorSet cantor = new CantorSet(depth);
            cantor.setVisible(true);
        });
        
        System.out.println("Программа завершена");
    }
}
