#ifndef BML_SRC_ERROR_H_
#define BML_SRC_ERROR_H_

void bml_error(const char *function, const char *reason);
void bml_error_default_handler(const char *function, const char *reason);
void bml_error_null_handler(const char *function, const char *reason);

#endif /* BML_SRC_ERROR_H_ */
