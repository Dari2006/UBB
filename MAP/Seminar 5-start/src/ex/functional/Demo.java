package ex.functional;

import java.util.List;

public class Demo {
    public static <E> void printArea(List<E> figures, Area<E> area){
        for(E figure : figures){
            System.out.println(area.compute(figure));
        }
    }


    static void main(String[] args) {
        List<Circle> circles = List.of(new Circle(4), new Circle(6), new Circle(5));

        System.out.println("anonymous area");
        Area<Circle> anonymousArea = new Area<Circle>() {
            @Override
            public double compute(Circle figure) {
                return figure.getRadius() * figure.getRadius() * Math.PI;
            }
        };

        System.out.println("lambda");

        Area<Circle> lambdaArea = c -> Math.PI * c.getRadius() * c.getRadius();

        System.out.println("reference area");
        Area<Circle> refArea = Circle::area;


    }
}

