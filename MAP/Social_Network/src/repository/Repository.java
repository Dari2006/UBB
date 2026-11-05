package repository;

import Domain.Entity;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

/**
 * common interface for CRUD operations
 * @param <ID> id of entity
 * @param <E>  entity type that we store
 */
public interface Repository<ID, E extends Entity<ID>> {

    E findById(ID id);

    Iterable<E> getAll();

    void save(E entity);

    void delete(ID id);

    void update(E entity);

    Iterable<ID> getKeys();

    default Iterable<E> findAll(Predicate<E> filter) {
        List<E> res = new ArrayList<>();
        for(E entity : getAll()){
            if(filter.test(entity)){
                res.add(entity);
            }
        }
        return res;
    }
}