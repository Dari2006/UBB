package repository.db;

import domain.User;
import domain.validators.Validator;
import repository.Repository;

public class UtilizatorDbRepository implements Repository<Long, User> {
    private final Validator<User> validator;
    private final String url;
    private final String username;
    private final String parola;

    public UtilizatorDbRepository(Validator<User> validator, String url, String username, String parola) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.parola = parola;
    }


    @Override
    public User findOne(Long aLong){
        throw new UnsupportedOperationException("findOne not implemented");

    }

    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("findOne not implemented");
    }

    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("findOne not implemented");
    }

    @Override
    public User delete(Long aLong) {
        throw new UnsupportedOperationException("findOne not implemented");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("findOne not implemented");
    }
}
