package validator;

/**
 * common interface for validators
 * @param <T>  entity to be validated
 */
@FunctionalInterface
public interface Validator<T> {
    void validate(T entity) throws ValidationException;

    default Validator<T> andThen(Validator<T> other) {
        return entity ->{
            validate(entity);
            other.validate(entity);
        };
    }
}
