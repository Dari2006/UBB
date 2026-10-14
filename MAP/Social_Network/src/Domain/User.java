package Domain;

public class User {
    private final int id;
    private String Username;
    private String email;

    public User(int id, String email, String username) {
        this.id = id;
        this.email = email;
        Username = username;
    }

    public int getId() {
        return id;
    }

    public String getUsername() {
        return Username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setUsername(String username) {
        Username = username;
    }
}
