package service;

import Domain.User;
import repository.Repository;
import validator.ServiceException;
import validator.ValidationException;
import validator.Validator;

import java.util.Iterator;
import java.util.Objects;

public class UserService {

    private Repository<Long, User> repository;
    private Validator<User> validator;
    private Long nextId;


    public UserService(Repository<Long, User> repository, Validator<User> validator) {
        this.repository = repository;
        this.validator = createValidator(validator);
        nextId = 1L;
    }

    Validator<User> createValidator(Validator<User> val1){
        Validator<User> v2 = val1.andThen(user->{
           if(user.getUsername() == null || user.getUsername().length() < 2){
               throw new ValidationException("username is too short");
           }
        });

        return v2;
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
        for(User user : repository.getAll()){
            if(Objects.equals(username, user.getUsername())){
                throw new ServiceException("username already exists");
            }
        }
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