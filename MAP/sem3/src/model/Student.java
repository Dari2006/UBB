package model;

import java.util.Objects;

public class Student implements Comparable<Student>{
    private  String name;
    private float medie;

    public Student(String name, float medie) {
        this.name = name;
        this.medie = medie;
    }

    @Override
    public String toString() {
        return super.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return Float.compare(medie, student.medie) == 0 && Objects.equals(name, student.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, medie);
    }

    @Override
    public int compareTo(Student o) {
        return this.name.compareTo(o.name); //alfabetic, necesar pt tree
    }

    public String getName() {
        return name;
    }

    public float getMedie() {
        return medie;
    }
}
