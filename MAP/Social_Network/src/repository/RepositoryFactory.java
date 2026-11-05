package repository;

import Domain.Entity;
import Domain.Friendship;
import Domain.User;
import repository.dbRepository.FriendshipDbRepository;
import repository.dbRepository.UserDbRepository;
import repository.fileRepository.FriendshipFileRepository;
import repository.fileRepository.UserFileRepository;
import validator.FriendshipValidator;
import validator.RepositoryException;
import validator.UserValidator;
import validator.Validator;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.Properties;
import java.util.function.Function;
import java.util.function.Supplier;

public class RepositoryFactory {
    private Properties properties;

    private Map<RepositoryType, Function<Validator<User>, InMemoryRepository<Long, User>>> userCreator;
    private Map<RepositoryType, Function<Validator<Friendship>, InMemoryRepository<Long, Friendship>>> friendshipCreator;

    public RepositoryFactory(Properties property) {
        this.properties = property;
        userCreator = new HashMap<>();
        friendshipCreator = new HashMap<>();

        populateMaps();
    }


    private void populateMaps(){
        userCreator.put(RepositoryType.MEMORY, userValidator -> {
            return new UserRepository((UserValidator) userValidator);
        });

        userCreator.put(RepositoryType.FILE, userValidator -> {
            return new UserFileRepository(properties.getProperty("users.file"), (UserValidator) userValidator);
        });

        friendshipCreator.put(RepositoryType.MEMORY, friendshipValidator -> {
           return new FriendshipRepository(friendshipValidator);
        });

        friendshipCreator.put(RepositoryType.FILE, friendshipValidator -> {
           return new FriendshipFileRepository(properties.getProperty("friendships.file"), (FriendshipValidator) friendshipValidator);
        });
    }

    /**
     * method that creates a user repository
     * @param validator, user validator
     * @return new user repository dependingon repository type specified in config file
     */
    public Repository<Long, User> createUserRepository(UserValidator validator){
        try{
            RepositoryType type = RepositoryType.valueOf(properties.getProperty("repository.type"));

            if(userCreator.get(type) == null){
                throw new RepositoryException("invalid repo type");
            }
            return userCreator.get(type).apply(validator);

        }
       catch(IllegalArgumentException e){
            throw new RepositoryException("invalid repo");
       }

    }

    /**
     * method that creates new friendship repository
     * @param validator, friendship validator
     * @return new friendship repository, based on specified type in config file
     */
    public Repository<Long, Friendship> createFriendshipRepository(FriendshipValidator validator){
        RepositoryType type = RepositoryType.valueOf(properties.getProperty("repository.type"));

        return friendshipCreator.get(type).apply(validator);
    }
}
