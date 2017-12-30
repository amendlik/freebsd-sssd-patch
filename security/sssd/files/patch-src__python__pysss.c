--- src/python/pysss.c.dist	2015-05-03 04:14:30.000000000 +0200
+++ src/python/pysss.c	2015-05-03 04:18:31.000000000 +0200
@@ -781,12 +781,14 @@
         goto fail;
     }
 
-    do {
+    ret = getgrouplist(username, pw->pw_gid, groups, &ngroups);
+    if (ret == -1) {
+        groups = realloc(groups, ngroups * sizeof(gid_t));
         ret = getgrouplist(username, pw->pw_gid, groups, &ngroups);
-        if (ret < ngroups) {
-            groups = realloc(groups, ngroups * sizeof(gid_t));
+        if (ret == -1) {
+            goto fail;
         }
-    } while (ret != ngroups);
+    }
 
     groups_tuple = PyTuple_New((Py_ssize_t) ngroups);
     if (groups_tuple == NULL) {

