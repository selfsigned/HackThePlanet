#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*auth; /* 0x08049aac */
void	*service; /* 0x08049ab0 */

int main(void)
{
	char cVar1;
	char *pcVar2;
	int iVar3;
	unsigned int uVar4;
	char *pbVar5;
	char *pbVar6;
	bool bVar7;
	char uVar8; //undefined
	char uVar9; //undefined
	bool bVar10;
	char uVar11; //undefined
	char bVar12;
	char buffer[5];
	char local_8b[2];
	char acStack_89[125];

	bVar12 = 0;
	do {
		printf("%p, %p \n", auth, service);
		pcVar2 = fgets((char *)buffer, 128, stdin);
		bVar7 = false;
		if (pcVar2 == NULL) {
			return 0;
		}
		iVar3 = 5;
		pbVar5 = buffer;
		pbVar6 = (char *)"auth ";
		do {
			if (iVar3 == 0)
				break;
			iVar3 -= 1;
			bVar7 = *pbVar5 < *pbVar6;
			bVar10 = (*pbVar5 == *pbVar6);
			pbVar5 = pbVar5 + (unsigned int)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (unsigned int)bVar12 * -2 + 1;
		} while (bVar10);
		uVar8 = 0;
		uVar11 = (!bVar7 && !bVar10) == bVar7;
		if ((bool)uVar11) {
			auth = malloc(4);
			*auth = 0;
			uVar4 = 0xffffffff;
			pcVar2 = local_8b;
			do {
				if (uVar4 == 0)
					break;
				uVar4 -= 1;
				cVar1 = *pcVar2;
				pcVar2 = pcVar2 + (unsigned int)bVar12 * -2 + 1;
			} while (cVar1 != '\0');
			uVar4 = ~uVar4 - 1;
			uVar8 = uVar4 < 30;
			uVar11 = uVar4 == 30;
			if (uVar4 < 31) {
				strcpy((char *)auth, local_8b);
			}
		}
		iVar3 = 5;
		pbVar5 = buffer;
		pbVar6 = (char *)"reset";
		do {
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			uVar8 = (*pbVar5 < *pbVar6);
			uVar11 = (*pbVar5 == *pbVar6);
			pbVar5 = pbVar5 + (unsigned int)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (unsigned int)bVar12 * -2 + 1;
		} while ((bool)uVar11);
		uVar9 = 0;
		uVar8 = (!(bool)uVar8 && !(bool)uVar11) == (bool)uVar8;
		if ((bool)uVar8) {
			free(auth);
		}
		iVar3 = 6;
		pbVar5 = buffer;
		pbVar6 = (char *)"service";
		do {
			if (iVar3 == 0)
				break;
			iVar3 -= 1;
			uVar9 = (*pbVar5 < *pbVar6);
			uVar8 = (*pbVar5 == *pbVar6);
			pbVar5 = pbVar5 + (unsigned int)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (unsigned int)bVar12 * -2 + 1;
		} while ((bool)uVar8);
		uVar11 = 0;
		uVar8 = (!(bool)uVar9 && !(bool)uVar8) == (bool)uVar9;
		if ((bool)uVar8) {
			uVar11 = ((char *)0xfffffff8 < buffer);
			uVar8 = (acStack_89 == NULL);
			service = strdup(acStack_89);
		}
		iVar3 = 5;
		pbVar5 = buffer;
		pbVar6 = (char *)"login";
		do {
			if (iVar3 == 0)
				break;
			iVar3 -= 1;
			uVar11 = *pbVar5 < *pbVar6;
			uVar8 = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (unsigned int)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (unsigned int)bVar12 * -2 + 1;
		} while ((bool)uVar8);
		if ((!(bool)uVar11 && !(bool)uVar8) == (bool)uVar11) {
			if (auth[8] == 0) {
				fwrite("Password:\n", 1, 10, stdout);
			}
			else {
				system("/bin/sh");
			}
		}
	} while (true);
}
