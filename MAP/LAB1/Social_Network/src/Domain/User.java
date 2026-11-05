package Domain;

import Domain.Entity;

import java.util.ArrayList;
import java.util.List;

public class User extends Entity<Long> {
    //unique identifiers: id, username
    private Long id;
    private String firstName;
    private String lastName;
    private String username;
    private List<Long> friendIds;

    public User(Long id, String firstName, String lastName, String username) {
        super(id);
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.username = username;
        this.friendIds = new ArrayList<>();
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public List<Long> getFriendIds() {
        return friendIds;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public void addFriend(Long friendId) {
        friendIds.add(friendId);
    }

    public void removeFriend(Long friendId) {
        friendIds.remove(friendId);
    }

    @Override
    public String toString() {
        return "@" + username + "(" + firstName + ", " + lastName + ")";
    }

    @Override
    public Long getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }
}