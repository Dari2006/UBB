package repository.fileRepository;

import Domain.Entity;
import Domain.User;
import validator.UserValidator;

public class UserFileRepository extends AbstractFileRepository {

    public UserFileRepository(String filename, UserValidator validator) {
        super(filename, validator);
    }

    @Override
    public Entity extractEntity(String line) {
        String[] args = line.split(";");
        Long id = Long.parseLong(args[0]);
        String firstName = args[1];
        String lastName = args[2];
        String username = args[3];
        return new User(id, firstName, lastName, username);
    }

    @Override
    public String parseEntity(Entity entity) {
        User user = (User) entity;
        String id = String.valueOf(user.getId());
        String firstName = user.getFirstName();
        String lastName = user.getLastName();
        String username = user.getUsername();
        return id+";"+firstName+";"+lastName+";"+username;
    }
}
