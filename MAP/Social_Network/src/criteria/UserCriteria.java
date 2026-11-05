package criteria;

import Domain.User;

import java.util.function.Predicate;

public class UserCriteria {
    public static Predicate<User> lastNameIs(String name){
        return user -> user.getLastName().equals(name);
    }

    public static Predicate<User> firstNameIs(String name){
        return user -> user.getFirstName().equals(name);
    }
    public static Predicate<User> usernameIs(String name){
        return user -> user.getUsername().equals(name);
    }
}
