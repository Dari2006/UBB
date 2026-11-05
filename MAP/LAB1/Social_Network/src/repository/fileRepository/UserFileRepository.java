package repository.fileRepository;

import Domain.Entity;
import Domain.User;
import com.sun.jdi.InvalidLineNumberException;
import validator.RepositoryException;
import validator.UserValidator;

public class UserFileRepository extends AbstractFileRepository<Long, User> {

    public UserFileRepository(String filename, UserValidator validator) {
        super(filename, validator, User::getUsername);
    }

    @Override
    public User extractEntity(String line) {
        String[] args = line.split(";");
        if(args.length != 4)
            throw new RepositoryException("invalid line");
        try {
            Long id = Long.parseLong(args[0]);
            String firstName = args[1];
            String lastName = args[2];
            String username = args[3];
            return new User(id, firstName, lastName, username);
        }
        catch (NumberFormatException e){
            throw new RepositoryException("invalid id");
        }
    }

    @Override
    public String parseEntity(User user) {
        String id = String.valueOf(user.getId());
        String firstName = user.getFirstName();
        String lastName = user.getLastName();
        String username = user.getUsername();
        return id+";"+firstName+";"+lastName+";"+username;
    }
}
