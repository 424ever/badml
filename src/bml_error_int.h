#ifndef BML_SRC_BML_ERROR_INTERNAL_H_
#define BML_SRC_BML_ERROR_INTERNAL_H_

void bml_error(const char *function, const char *reason);
void bml_error_default_handler(const char *function, const char *reason);
void bml_error_null_handler(const char *function, const char *reason);

#endif /* BML_SRC_BML_ERROR_INTERNAL_H_ */
