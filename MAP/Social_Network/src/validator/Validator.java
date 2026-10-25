package validator;

/**
 * common interface for validators
 * @param <T>  entity to be validated
 */
public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}
