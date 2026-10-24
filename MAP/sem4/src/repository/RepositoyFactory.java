package repository;

import domain.User;
import domain.validators.Validator;
import repository.db.UtilizatorDbRepository;
import repository.file.UserFileRepository;

import java.util.Locale;
import java.util.Properties;

public class RepositoyFactory {
    private Properties properties;

    public RepositoyFactory(Properties properties) {
        this.properties = properties;
    }

    public Repository<Long, User> createUserRepository(Validator<User> valdiator){
        String property = properties.getProperty("repository.type");
        RepositoryType type = RepositoryType.valueOf(property.trim().toUpperCase());

        switch(type){
            case MEMORY:
                return new InMemoryRepository<>(valdiator);
            case FILE:
                return new UserFileRepository<>(valdiator,properties.getProperty("file.name"));
            case DATABASE:
                return new UtilizatorDbRepository(valdiator);
            default:
                throw new IllegalArgumentException("invalid repo ype");
        }
    }
}
