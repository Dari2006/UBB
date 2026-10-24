package repository.fileRepository;

import Domain.Entity;
import Domain.Friendship;

import java.time.LocalDateTime;

public class FriendshipFileRepository extends AbstractFileRepository{
    public FriendshipFileRepository(String filename) {
        super(filename);
    }

    @Override
    public Entity extractEntity(String line) {
        String[] args = line.split(";");

        Long id = Long.parseLong(args[0]);
        Long id1 = Long.parseLong(args[1]);
        Long id2 = Long.parseLong(args[2]);
        LocalDateTime friendsSince = LocalDateTime.parse(args[3]);
        return new Friendship(id, id1, id2, friendsSince);
    }

    @Override
    public String parseEntity(Entity entity) {
        Friendship f = (Friendship) entity;
        String id = String.valueOf(f.getId());
        String id1 = String.valueOf(f.getUser1Id());
        String id2 = String.valueOf(f.getUser2Id());
        String friendsSince = String.valueOf(f.getFriendsSince());
        return id+";"+id1+";"+id2+";"+friendsSince;
    }
}
