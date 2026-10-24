package validator;

import Domain.User;

public class UserValidator implements Validator<User> {

    @Override
    public void validate(User user) {

        if (user == null)
            throw new ValidationException("User cannot be null");

        if (user.getId() == null)
            throw new ValidationException("ID cannot be null");

        if (user.getFirstName() == null || user.getFirstName().isEmpty())
            throw new ValidationException("First name cannot be empty");

        if (user.getLastName() == null || user.getLastName().isEmpty())
            throw new ValidationException("Last name cannot be empty");
        if(user.getUsername() == null || user.getUsername().isEmpty())
            throw new ValidationException("Username can not be empty");
    }
}