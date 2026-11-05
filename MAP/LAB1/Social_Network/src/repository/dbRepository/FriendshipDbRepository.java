package repository.dbRepository;

import Domain.Friendship;
import Domain.User;
import repository.Repository;
import validator.Validator;

public class FriendshipDbRepository implements Repository<Long, Friendship> {
    private Validator<Friendship> validator;
    private String url;
    private String user;
    private String password;

    public FriendshipDbRepository(Validator<Friendship> validator, String password, String user, String url) {
        this.validator = validator;
        this.password = password;
        this.user = user;
        this.url = url;
    }

    @Override
    public Friendship findById(Long aLong) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterable<Friendship> getAll() {
        throw new UnsupportedOperationException();
    }

    @Override
    public void save(Friendship entity) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void delete(Long aLong) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void update(Friendship entity) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterable<Long> getKeys() {
        throw new UnsupportedOperationException();
    }
}
