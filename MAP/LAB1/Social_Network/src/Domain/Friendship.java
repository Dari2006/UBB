package Domain;

import java.time.LocalDateTime;

public class Friendship extends Entity<Long> {

    private Long user1Id;
    private Long user2Id;
    private LocalDateTime friendsSince;

    public Friendship(Long id, Long user1Id, Long user2Id, LocalDateTime friendsSince) {
        super(id);
        this.user1Id = user1Id;
        this.user2Id = user2Id;
        this.friendsSince = friendsSince;
    }

    public Long getUser1Id() {
        return user1Id;
    }

    public Long getUser2Id() {
        return user2Id;
    }

    public LocalDateTime getFriendsSince() {
        return friendsSince;
    }

    @Override
    public String toString() {
        return "Friendship{" +
                "id=" + getId() +
                ", user1Id=" + user1Id +
                ", user2Id=" + user2Id +
                "friends since: " + friendsSince +
                '}';
    }
}
