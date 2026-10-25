package repository;

import Domain.User;
import validator.UserValidator;
import validator.Validator;

public class UserRepository extends InMemoryRepository<Long, User> {

    public UserRepository(UserValidator validator) {
        super(validator);
    }
}
