package repository;

import Domain.Friendship;

import java.util.ArrayList;
import java.util.List;

public class FriendshipRepository {
    private List<Friendship> friendships = new ArrayList<>();

    public List<Friendship> getFriendships(){
        return friendships;
    }

    public void addFriendship(Friendship friendship){
        friendships.add(friendship);
    }

    public void deleteFriendship(Friendship friendship){
        friendships.remove(friendship);
    }

    boolean isEmpty(){
        return friendships.isEmpty();
    }
}
