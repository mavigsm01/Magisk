#include "magiskpolicy.h"
#include "sepolicy.h"

int sepol_allow(const char *s, const char *t, const char *c, const char *p) {
//	 printf("allow %s %s %s %s\n", s, t, c, p);
	return add_rule(s, t, c, p, AVTAB_ALLOWED, 0);
}

int sepol_deny(const char *s, const char *t, const char *c, const char *p) {
	// printf("deny %s %s %s %s\n", s, t, c, p);
	return add_rule(s, t, c, p, AVTAB_ALLOWED, 1);
}

int sepol_auditallow(const char *s, const char *t, const char *c, const char *p) {
	// printf("auditallow %s %s %s %s\n", s, t, c, p);
	return add_rule(s, t, c, p, AVTAB_AUDITALLOW, 0);
}

int sepol_auditdeny(const char *s, const char *t, const char *c, const char *p) {
	// printf("auditdeny %s %s %s %s\n", s, t, c, p);
	return add_rule(s, t, c, p, AVTAB_AUDITDENY, 0);
}

int sepol_typetrans(const char *s, const char *t, const char *c, const char *d, const char *o) {
	if (o == nullptr) {
		// printf("add_trans %s %s %s %s\n", s, t, c ,d);
		return add_transition(s, t, c, d);
	} else {
		// printf("add_file_trans %s %s %s %s %s\n", s, t, c ,d, o);
		return add_file_transition(s, t, c, d, o);
	}
}

int sepol_allowxperm(const char *s, const char *t, const char *c, const char *range) {
	// printf("allowxperm %s %s %s %s\n", s, t, c, range);
	return add_xperm_rule(s, t, c, range, AVTAB_XPERMS_ALLOWED, 0);
}

int sepol_auditallowxperm(const char *s, const char *t, const char *c, const char *range) {
	// printf("auditallowxperm %s %s %s %s\n", s, t, c, range);
	return add_xperm_rule(s, t, c, range, AVTAB_XPERMS_AUDITALLOW, 0);
}

int sepol_dontauditxperm(const char *s, const char *t, const char *c, const char *range) {
	// printf("dontauditxperm %s %s %s %s\n", s, t, c, range);
	return add_xperm_rule(s, t, c, range, AVTAB_XPERMS_DONTAUDIT, 0);
}

int sepol_permissive(const char *s) {
	// printf("permissive %s\n", s);
	return set_domain_state(s, 1);
}

int sepol_enforce(const char *s) {
	// printf("enforce %s\n", s);
	return set_domain_state(s, 0);
}

int sepol_create(const char *s) {
	// printf("create %s\n", s);
	return create_domain(s);
}

int sepol_attradd(const char *s, const char *a) {
	// printf("attradd %s %s\n", s, a);
	return add_typeattribute(s, a);
}

int sepol_exists(const char *source) {
	return hashtab_search(policydb->p_types.table, source) != nullptr;
}
