import domain.Grade;
import domain.Homework;
import domain.Student;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    private static List<Student> getStudents() {
        Student s1 = new Student("andrei", 221);
        s1.setId(1L);
        Student s2 = new Student("dan", 222);
        s2.setId(2L);
        Student s3 = new Student("gigi", 221);
        s3.setId(3L);
        Student s4 = new Student("costel", 222);
        s4.setId(4L);
        return Arrays.asList(s1, s2, s3, s4);
    }

    private static List<Homework> getHomeworks() {
        return Arrays.asList(
                new Homework("t1", "desc1"),
                new Homework("t2", "desc2"),
                new Homework("t3", "desc3"),
                new Homework("t4", "desc4")
        );
    }


    public static void report1(List<Grade> grades, String name){
        //filtrare

        List<Grade> filteredGrades = grades.stream().filter(g -> g.getStudent().getName().contains(name))
                .collect(Collectors.toList());

        //grupare dupa medie

        Map<String, Double> byAverage = filteredGrades.stream().
                collect(Collectors.groupingBy(g->g.getStudent().getName(),
                        Collectors.averagingDouble(g-> g.getValue())));

        //sortare
        byAverage.entrySet().stream()
                .sorted((a,b)->Double.compare(b.getValue(), a.getValue()))
                .forEach(e-> System.out.println("Stud: " + e.getKey() + " medie: " + e.getValue()));




    }

    public static void report2(List<Grade> grades, String name){
        //filtrare

        List<Grade> filteredGrades = grades.stream().filter(g -> g.getTeacher().contains(name))
                .collect(Collectors.toList());

        //grupare dupa medie

        Map<String, Double> byAverage = filteredGrades.stream().
                collect(Collectors.groupingBy(g->g.getTeacher(),
                        Collectors.averagingDouble(g-> g.getValue())));

        //sortare
        byAverage.entrySet().stream()
                .sorted((a,b)->Double.compare(b.getValue(), a.getValue()))
                .forEach(e-> System.out.println("Stud: " + e.getKey() + " medie: " + e.getValue()));




    }


    public static void report3(List<Grade> grades, int grupa){
        //filtrare grupa
        List<Grade> filteredGrades = grades.stream()
                .filter(g->g.getStudent().getGroup()==grupa).toList();








    }



    public static void report4(List<Grade> grades, String n){

        List<Grade> filtered = grades.stream().filter(g->String.valueOf(g.getStudent().getGroup()).startsWith(n)).toList();

        Map<Integer, Double> integerDoubleMap = filtered.stream().collect(Collectors.groupingBy(g -> g.getStudent().getGroup(), Collectors.averagingDouble(g -> g.getValue())));


    }


public static void report5(List<Grade> grades){
        Map<Integer, List<Grade>>byGroup = grades.stream().
                collect(Collectors.groupingBy(g->g.getStudent().getGroup()));
        
        
        byGroup.entrySet().
                stream().
                collect(Collectors.toMap(e->e.getKey(), 
                        e->{
                    List<Grade> gradesByGroup = e.getValue();
                    double average = gradesByGroup.stream().mapToDouble(g->g.getValue()).average().orElse(0);
                    long nrStudents = gradesByGroup.stream().map(g->g.getStudent().getName()).distinct().count();
                    return average/nrStudents;
                        }));
}
    private static List<Grade> getGrades(List<Student> stud, List<Homework> homeworks) {
        return Arrays.asList(
                new Grade(stud.get(0), homeworks.get(0), 10d, LocalDate.of(2019, 11, 2), "profesor1"),
				new Grade(stud.get(0), homeworks.get(1), 10d, LocalDate.of(2019, 11, 2), "profesor2"),
                new Grade(stud.get(1), homeworks.get(0), 9d, LocalDate.of(2019, 11, 2).minusWeeks(1), "profesor1"),
                new Grade(stud.get(1), homeworks.get(1), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Grade(stud.get(1), homeworks.get(2), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Grade(stud.get(2), homeworks.get(1), 7d, LocalDate.of(2019, 10, 28), "profesor1"),
                new Grade(stud.get(2), homeworks.get(3), 9d, LocalDate.of(2019, 10, 27), "profesor2"),
                new Grade(stud.get(1), homeworks.get(3), 10d, LocalDate.of(2019, 10, 29), "profesor2")
        );
    }
    public static void main(String[] args) {
        List<Grade> grades = getGrades(getStudents(), getHomeworks());
        grades.forEach(System.out::println);
        System.out.println("report1");
        report1(grades, "a");
        System.out.println("\n--------------\n");
        System.out.println("report2");
        report2(grades, "o");

        System.out.println("\n-------------\n");




    }
}