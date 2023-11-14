#ifndef BML_SRC_BML_ERROR_H_
#define BML_SRC_BML_ERROR_H_

typedef void bml_err_handler_t(const char *function, const char *reason);

bml_err_handler_t *bml_set_err_handler(bml_err_handler_t *);
bml_err_handler_t *bml_set_err_handler_off(void);
bml_err_handler_t *bml_get_err_handler(void);

#endif
