package repository;

import Domain.User;

import java.util.ArrayList;
import java.util.List;

public class UserRepository {
    private List<User> users = new ArrayList<>();

    public List<User> getUsers(){
        return users;
    }

    public void addUser(User user){
        users.add(user);
    }

    public void deleteUser(User user){
        users.remove(user);
    }

    public void updateUser(int index, User newUser){
        users.set(index, newUser);
    }

    public boolean isEmpty(){
        return users.isEmpty();
    }
}
