# libnginx

Extract data structure from Nginx

Nginx version 1.10.0

## How To Use

**Install**

	git clone https://github.com/AlexWoo/libnginx.git
	cd libnginx
	make && make install
	grep "/usr/local/lib" /etc/ld.so.conf.d/local.conf || echo "/usr/local/lib" >> /etc/ld.so.conf.d/local.conf
	ldconfig

**Link to your program**

	gcc -g -o aa test.c -lnginx

**test.c samples**

	#include <ngx_config.h>
	#include <ngx_core.h>
	
	#define  NGX_OK          0
	#define  NGX_ERROR      -1
	
	typedef struct
	{
	    ngx_str_t            request_line;
	    ngx_str_t            pull_host;
	    ngx_pool_t          *pool;
	} ngx_http_pull_ctx_t;
	
	ngx_int_t ngx_http_pull_add_host_header(ngx_http_pull_ctx_t *ctx)
	{
	//    if (ctx->pull_url == NULL) {
	//        return NGX_ERROR;
	//    }
	    u_char      *pos, *last, *end;
	    size_t       len, newhostlen;
	
	    ngx_str_t *request_line = &ctx->request_line;
	    if(request_line->len <= 2){
	        return NGX_ERROR;
	    }
	
	    newhostlen = ctx->pull_host.len + 6;
	    pos = ngx_strnstr(request_line->data, (char *)"Host:", request_line->len);
	    printf("%p request_line->len: %d newhostlen: %d\n", pos, request_line->len, newhostlen);
	    if (pos == NULL) {
	
	        u_char *newdata = ngx_palloc(ctx->pool, request_line->len + newhostlen + 4);
	        pos = ngx_cpymem(newdata, request_line->data, request_line->len);
	        ngx_snprintf(pos, newhostlen + 4, "Host: %V\r\n\r\n", &ctx->pull_host);
	        request_line->data = newdata;
	        request_line->len = request_line->len + newhostlen + 4;
	    } else {
	
	        last = ngx_strnstr(pos, (char *)"\r\n", request_line->len);
	        end = request_line->data + request_line->len;
	        len = last - pos;
	        if (newhostlen == len) {
	            ngx_snprintf(pos, newhostlen, "Host: %V", &ctx->pull_host);
	        } else if (newhostlen < len) {
	            ngx_snprintf(pos, newhostlen, "Host: %V", &ctx->pull_host);
	            ngx_memcpy(pos + newhostlen, last, end - last);
	            request_line->len = request_line->len + (newhostlen - len);
	        } else {
	            u_char *newdata = ngx_palloc(ctx->pool, request_line->len + (newhostlen - len));
	            pos = ngx_cpymem(newdata, request_line->data, pos - request_line->data);
	            ngx_snprintf(pos, newhostlen, "Host: %V", &ctx->pull_host);
	            ngx_memcpy(pos + newhostlen, last, end - last);
	            request_line->data = newdata;
	            request_line->len = request_line->len + (newhostlen - len);
	        }
	    }
	
	    return NGX_OK;
	}
	
	int main()
	{
	    ngx_http_pull_ctx_t ctx;
	    ctx.pool = ngx_create_pool(128, NULL);
	    ctx.pull_host.data = "www.baidu.com";
	    ctx.pull_host.len = sizeof("www.baidu.com") - 1;
	
	    /* No Host */
	    ctx.request_line.data = ngx_palloc(ctx.pool, strlen("PUT / HTTP/1.1\r\n"));
	    ctx.request_line.len = sizeof("PUT / HTTP/1.1\r\n") - 1;
	    memcpy(ctx.request_line.data, "PUT / HTTP/1.1\r\n", ctx.request_line.len);
	    printf("before func: %s\n", ctx.request_line.data);
	    ngx_http_pull_add_host_header(&ctx);
	    printf("after func: %s\n", ctx.request_line.data);
	    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	
	    /* Host equal */
	    ctx.request_line.data = ngx_palloc(ctx.pool, strlen("PUT / HTTP/1.1\r\nHost: www.test1.com\r\nConnection: close\r\n\r\n"));
	    ctx.request_line.len = sizeof("PUT / HTTP/1.1\r\nHost: www.test1.com\r\nConnection: close\r\n\r\n") - 1;
	    memcpy(ctx.request_line.data, "PUT / HTTP/1.1\r\nHost: www.test1.com\r\nConnection: close\r\n\r\n", ctx.request_line.len);
	    printf("before func: %s\n", ctx.request_line.data);
	    ngx_http_pull_add_host_header(&ctx);
	    printf("after func: %s\n", ctx.request_line.data);
	    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	
	    /* Host less */
	    ctx.request_line.data = ngx_palloc(ctx.pool, strlen("PUT / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n"));
	    ctx.request_line.len = sizeof("PUT / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n") - 1;
	    memcpy(ctx.request_line.data, "PUT / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n", ctx.request_line.len);
	    printf("before func: %s\n", ctx.request_line.data);
	    ngx_http_pull_add_host_header(&ctx);
	    printf("after func: %s\n", ctx.request_line.data);
	    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	
	    /* Host great */
	    ctx.request_line.data = ngx_palloc(ctx.pool, strlen("PUT / HTTP/1.1\r\nHost: www.qq.com\r\nConnection: close\r\n\r\n"));
	    ctx.request_line.len = sizeof("PUT / HTTP/1.1\r\nHost: www.qq.com\r\nConnection: close\r\n\r\n") - 1;
	    memcpy(ctx.request_line.data, "PUT / HTTP/1.1\r\nHost: www.qq.com\r\nConnection: close\r\n\r\n", ctx.request_line.len);
	    printf("before func: %s\n", ctx.request_line.data);
	    ngx_http_pull_add_host_header(&ctx);
	    printf("after func: %s\n", ctx.request_line.data);
	    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	
	    /* Host equal, Host at end*/
	    ctx.request_line.data = ngx_palloc(ctx.pool, strlen("PUT / HTTP/1.1\r\nHost: www.test1.com\r\n\r\n"));
	    ctx.request_line.len = sizeof("PUT / HTTP/1.1\r\nHost: www.test1.com\r\n\r\n") - 1;
	    memcpy(ctx.request_line.data, "PUT / HTTP/1.1\r\nHost: www.test1.com\r\n\r\n", ctx.request_line.len);
	    printf("before func: %s\n", ctx.request_line.data);
	    ngx_http_pull_add_host_header(&ctx);
	    printf("after func: %s\n", ctx.request_line.data);
	    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	
	    /* Host less, Host at end */
	    ctx.request_line.data = ngx_palloc(ctx.pool, strlen("PUT / HTTP/1.1\r\nHost: www.sina.com.cn\r\n\r\n"));
	    ctx.request_line.len = sizeof("PUT / HTTP/1.1\r\nHost: www.sina.com.cn\r\n\r\n") - 1;
	    memcpy(ctx.request_line.data, "PUT / HTTP/1.1\r\nHost: www.sina.com.cn\r\n\r\n", ctx.request_line.len);
	    printf("before func: %s\n", ctx.request_line.data);
	    ngx_http_pull_add_host_header(&ctx);
	    printf("after func: %s\n", ctx.request_line.data);
	    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	
	    /* Host great, Host at end */
	    ctx.request_line.data = ngx_palloc(ctx.pool, strlen("PUT / HTTP/1.1\r\nHost: www.qq.com\r\n\r\n"));
	    ctx.request_line.len = sizeof("PUT / HTTP/1.1\r\nHost: www.qq.com\r\n\r\n") - 1;
	    memcpy(ctx.request_line.data, "PUT / HTTP/1.1\r\nHost: www.qq.com\r\n\r\n", ctx.request_line.len);
	    printf("before func: %s\n", ctx.request_line.data);
	    ngx_http_pull_add_host_header(&ctx);
	    printf("after func: %s\n", ctx.request_line.data);
	    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	}
