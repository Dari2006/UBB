package service;

import Domain.User;
import repository.Repository;
import validator.Validator;

import java.util.Iterator;

public class UserService {

    private Repository<Long, User> repository;
    private Validator<User> validator;
    private Long nextId;


    public UserService(Repository<Long, User> repository, Validator<User> validator) {
        this.repository = repository;
        this.validator = validator;
        nextId = 1L;
    }

    private Long generateId(){
        Iterable<Long> keys = repository.getKeys();
        Long max = 0L;
        for (Long id : keys) {
            if (id > max) {
                max = id;
            }
        }
        return max + 1;
    }

    public void addUser(String firstName, String lastName, String username) {
        User user = new User(
                generateId(),
                firstName,
                lastName,
                username
        );

        validator.validate(user);
        repository.save(user);
    }

    public Iterable<User> getAllUsers() {
        return repository.getAll();
    }

    public User getUserById(Long id) {
        return repository.findById(id);
    }

    public void deleteUser(Long id) {

        repository.delete(id);
    }

    public void updateUser(User user) {
        validator.validate(user);
        repository.update(user);
    }
}