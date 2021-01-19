/**
 * Get temporary variable from stack 
 */
extern char *newvar();

/**
 * Recycle variable bac to stack 
 */
extern void freevar(char *);