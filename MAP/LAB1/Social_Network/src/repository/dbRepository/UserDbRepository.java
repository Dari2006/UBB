package repository.dbRepository;

import Domain.User;
import repository.Repository;
import validator.Validator;

public class UserDbRepository implements Repository<Long, User> {
    Validator<User> validator;
    String url;
    String user;
    String password;

    public UserDbRepository(Validator<User> valdiator, String url, String password, String user) {
        this.validator = valdiator;
        this.url = url;
        this.password = password;
        this.user = user;
    }

    @Override
    public User findById(Long aLong) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterable<User> getAll() {
        throw new UnsupportedOperationException();
    }

    @Override
    public void save(User entity) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void delete(Long aLong) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void update(User entity) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterable<Long> getKeys() {
        throw new UnsupportedOperationException();
    }
}
