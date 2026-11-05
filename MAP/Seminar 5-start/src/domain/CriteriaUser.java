package domain;

import java.util.function.Predicate;

public class CriteriaUser {
    public static Predicate<User> firstNameStartsWith(String prefix){
        return u->u.getFirstName().startsWith(prefix);
    }

    public static Predicate<User> hasLastName(String name){
        return u->u.getLastName().equals(name);
    }

    public static Predicate<User> hasAtleastFriends(int n){

    }

    public static Predicate<User> withoutFriends(User u){

    }
}
