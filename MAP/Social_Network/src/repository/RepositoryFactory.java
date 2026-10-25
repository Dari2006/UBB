package repository;

import Domain.Friendship;
import Domain.User;
import repository.dbRepository.FriendshipDbRepository;
import repository.dbRepository.UserDbRepository;
import repository.fileRepository.FriendshipFileRepository;
import repository.fileRepository.UserFileRepository;
import validator.FriendshipValidator;
import validator.UserValidator;
import validator.Validator;

import java.util.Locale;
import java.util.Properties;

public class RepositoryFactory {
    private Properties properties;

    public RepositoryFactory(Properties property) {
        this.properties = property;

    }

    public Repository<Long, User> createUserRepository(UserValidator valdiaotr){
        String property = properties.getProperty("repository.type");
        RepositoryType type = RepositoryType.valueOf(property.trim().toUpperCase());

        switch(type){
            case MEMORY:
                return new UserRepository(valdiaotr);
            case FILE:
                return new UserFileRepository(properties.getProperty("users.file"), (UserValidator) valdiaotr);
            case DATABASE:
                return new UserDbRepository(valdiaotr, properties.getProperty("db.url"),
                        properties.getProperty("db.user"),
                        properties.getProperty("db.password"));
            default:
                throw new IllegalArgumentException("invalid repo type");
        }
    }

    public Repository<Long, Friendship> createFriendshipRepository(FriendshipValidator valdiaotr){
        String property = properties.getProperty("repository.type");
        RepositoryType type = RepositoryType.valueOf(property.trim().toUpperCase());

        switch(type){
            case MEMORY:
                return new FriendshipRepository(valdiaotr);
            case FILE:
                return new FriendshipFileRepository(properties.getProperty("friendships.file"), valdiaotr);
            case DATABASE:
                return new FriendshipDbRepository(valdiaotr, properties.getProperty("db.url"),
                        properties.getProperty("db.user"),
                        properties.getProperty("db.password"));
            default:
                throw new IllegalArgumentException("invalid repo type");
        }
    }
}
