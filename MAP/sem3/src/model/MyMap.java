package model;

import java.util.*;

public class MyMap{
    private Map<Integer, List<Student>> map;

    static class GradeComparator implements Comparator<Student>{

        @Override
        public int compare(Integer o1, Integer o2) {
            return Integer.compare(o1, o2);
        }

        @Override
        public int compare(Student o1, Student o2) {
            return 0;
        }
    }



}
