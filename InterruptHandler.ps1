# �����ļ�·��
$filePath = "Core/Src/stm32f1xx_it.c"

# ��ȡ�ļ�����Ϊ����
$fileContent = Get-Content $filePath

# ����Ҫɾ���ĺ�����ʼ�ͽ������
$functionsToRemove = @(
    @{ StartMarker = "void SVC_Handler(void)"; EndMarker = "}" },
    @{ StartMarker = "void PendSV_Handler(void)"; EndMarker = "}" }
)

# ��Ǳ���
$insideTargetBlock = $false
$modifiedContent = @()
$startMarkerFound = $false

# �����ļ����ݣ����м��
foreach ($line in $fileContent) {
    # ����Ƿ��Ǻ�������ʼ���
    foreach ($function in $functionsToRemove) {
        if ($line -like "*$($function.StartMarker)*") {
            $insideTargetBlock = $true
            $startMarkerFound = $true
            break
        }
    }

    # ���δ����Ŀ��飬��������
    if (-not $insideTargetBlock) {
        $modifiedContent += $line
    }

    # �����Ŀ����У�����Ƿ񵽴�������
    if ($insideTargetBlock -and $line -like "*$($function.EndMarker)*") {
        $insideTargetBlock = $false
    }
}

# ��������һ����ʼ��Ǳ��ҵ�ʱ��д���ļ�
if ($startMarkerFound) {
    $modifiedContent | Set-Content $filePath
    Write-Host "Ŀ�꺯����ɾ������д���ļ���$filePath"
} else {
    Write-Host "δ�ҵ��κ�Ŀ�꺯�����ļ�δ�޸ġ�"
}
