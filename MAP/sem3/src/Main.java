import model.Student;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
void main() {
    Student s1 = new Student("dan", 2323);
    Student s2 = new Student("fdan", 23);
    Set<Student>treeset = new TreeSet<>();
    treeset.add(s1);

    Comparator<Student>comparator = new Comparator<Student>() {
        @Override
        public int compare(Student o2, Student o1) {
            return 0;
        }
    };

    Set<Student>setwithcomp = new TreeSet<>(comparator);   //set cu comparator

    Map<String, Student>map = new HashMap<>();
    map.put(s1.getName(), s1);
    map.put(s2.getName(), s2);

    //for(Map.Entry(String, Student) entry : map.entrySet()){

    //}

    List<Student> list = new ArrayList<>();
    list.add(s1);
    list.add(s2);
    Iterator<Student> it = list.iterator();

    while(it.hasNext()){
        Student student = it.next();
        System.out.println(student);
    }
}
