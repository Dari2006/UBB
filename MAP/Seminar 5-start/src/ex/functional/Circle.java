package ex.functional;

public class Circle {
    private double radius;


    public double getRadius() {
        return radius;
    }

    public Circle(double radius) {
        this.radius = radius;
    }

    public static double area(Circle c){
        return Math.PI * c.getRadius() * c.getRadius();
    }
}
