package ex.functional;

public class Square {
    private double side;

    public double getSide() {
        return side;
    }

    public Square(double side) {
        this.side = side;
    }

    public double area(Square s){
        return s.getSide() * s.getSide();
    }
}
