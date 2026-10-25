package repository;

import Domain.Entity;

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
}