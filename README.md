
-------------------------------------------
PRE-FILTER-1    BLOCKMOVE
-------------------------------------------

Author : V01G04A81 Viktor Glebov

***Block Move / Transform***

## Overview


**Block Move / Transform**  
Transformation filter based on a counter-driven operation.
*Operations based on counter*
This pre-filter is designed to rearrange data blocks in a deterministic manner to improve compression efficiency when used with standard compressors (LZMA, ZIP, 7z, etc.).



## Parameters

| Parameter           | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| `<filename_in>`    | Input file name                                                             |
| `<offset_bytes>`   | Byte offset within the source file — starting point for transformation      |
| `<transform.yaml>` | Transformation configuration file (YAML format)                             |
| `<filename_out>`   | Output file name                                                            |


---
#### Test Methodology

1. For each image, transformation filters were applied:  
   - `zx_filter_a`, `zx_filter_b` for examples 1–6  
   - `cl_filter_a`, `cl_filter_b` for examples 7–8  

2. As a result, the following output directories were generated:  
   - `results1` - `results8`  
   - `results1a` - `results8a`  
   - `results1b` - `results8b`  

3. All output data was compressed using a set of compressors:  
   `zip`, `arj`, `7zip`, `xz`, and others  

4. Compression results were collected and organized into comparison tables  

---

## Visual Samples


| <img src="docs/example1.png" width="400"><br>`example1.scr`<br>HEWSON    | <img src="docs/example2.png" width="400"><br>`example2.scr`<br>Jarlaxe    | <img src="docs/example3.png" width="400"><br>`example3.scr`<br>Manu       |
| ------------------------------------------------------------------------ | ------------------------------------------------------------------------- | ------------------------------------------------------------------------- |
| <img src="docs/example4.png" width="400"><br>`example4.scr`<br>moroz1999 | <img src="docs/example5.png" width="400"><br>`example5.scr`<br>Rado Javor | <img src="docs/example6.png" width="400"><br>`example6.scr`<br>mr r0ckers |



| Preview                                   | File           | Author     |
| ----------------------------------------- | -------------- | ---------- |
| <img src="docs/example7.png" width="600"> | `example7.bin` | V01G04A81  |
| <img src="docs/example8.png" width="600"> | `example8.bin` | V01G04A81  |

---
#### Test Files

	example1.scr		HEWSON - Exolon Title
	example2.scr		Jarlaxe - Tokimal (2021).scr
	example3.scr		Manu - Sven's home in the snow (2021).scr
	example4.scr		moroz1999 - Crystal Kingdom Dizzy in-game 01 (2017).scr
	example5.scr		Rado Javor - ZX602 (1994).scr
	example6.scr		mr r0ckers - Blue Surf (2015) (Chaos Constructions 2015, 1).scr
	screen7.scr 		V01G04A81 Exoloneur Test Cells
	screen8.scr 		V01G04A81 Custom Font 8x8


---

## Notes

- The transformation operates deterministically based on a counter.
- Designed as a **pre-processing step** before compression.
- Particularly effective on structured pixel data (e.g., ZX Spectrum screens).

---

## Compression Benchmark

> Values represent: **original → transformed → fragmented**

| Базовый файл (размер)     | LZMA               | XZ                 | 7z                 | RAR                | GZ                 | BZ2                | ZIP                | ARJ                |
|---------------------------|--------------------|--------------------|--------------------|--------------------|--------------------|--------------------|--------------------|--------------------|
| example1.scr (6912)       | 1876 / 1648 / 1348 | 1924 / 1696 / 1396 | 1988 / 1784 / 1464 | 2115 / 1953 / 1524 | 2163 / 2193 / 1464 | 2367 / 2350 / 1777 | 2306 / 2337 / 1608 | 2329 / 2374 / 1618 |
| example2.scr (6912)       | 5433 / 5360 / 4999 | 5480 / 5404 / 5044 | 5545 / 5490 / 5137 | 5656 / 5608 / 5327 | 5493 / 5467 / 5215 | 6127 / 6117 / 5561 | 5636 / 5611 / 5359 | 5602 / 5570 / 5317 |
| example3.scr (6912)       | 2591 / 2465 / 2151 | 2636 / 2512 / 2196 | 2702 / 2576 / 2262 | 2770 / 2663 / 2294 | 2792 / 2718 / 2259 | 3057 / 3048 / 2690 | 2935 / 2862 / 2403 | 2914 / 2838 / 2384 |
| example4.scr (6912)       | 1751 / 1592 / 1049 | 1796 / 1640 / 1096 | 1862 / 1721 / 1168 | 1897 / 1816 / 1205 | 1949 / 1992 / 1146 | 2211 / 2196 / 1464 | 2092 / 2136 / 1289 | 2095 / 2134 / 1263 |
| example5.scr (6912)       | 4208 / 4039 / 3906 | 4256 / 4084 / 3952 | 4363 / 4172 / 4027 | 4479 / 4354 / 4058 | 4368 / 4285 / 4056 | 4923 / 4909 / 4603 | 4511 / 4429 / 4200 | 4498 / 4413 / 4183 |
| example6.scr (6912)       | 1981 / 1911 / 1841 | 2028 / 1956 / 1888 | 2108 / 2033 / 1962 | 2117 / 2048 / 2022 | 2099 / 2050 / 1990 | 2253 / 2272 / 2192 | 2242 / 2194 / 2134 | 2224 / 2165 / 2113 |
| example7.bin (16384)      | 1803 / 1852 / 1723 | 1848 / 1900 / 1768 | 1561 / 1923 / 1828 | 2329 / 2304 / 2784 | 3203 / 3133 / 2764 | 3688 / 3704 / 3381 | 3346 / 3277 / 2908 | 3415 / 3336 / 2939 |
| example8.bin (16384)      | 1688 / 1730 / 1579 | 1736 / 1776 / 1624 | 1780 / 1814 / 1682 | 1914 / 1948 / 1766 | 1953 / 1995 / 1866 | 1949 / 1957 / 1789 | 2096 / 2139 / 2010 | 2078 / 2115 / 2059 |



<br>


---
**Application flow**

	1. PARSE INPUT PARAMETERS
	|
	2. LOAD ORIGINAL               ( to BLOCK #1 - SOURCE )
	|
	3. CLONE                       ( to BLOCK #2 - DESTINATION )
	|
	4. TRANSFORM                   ( According to settings array )
	|
	5. SAVE TRANSFORMED            ( BLOCK #2 )


---
##### Описание фильтров ( параметров ) трансформации :

	zx_filter_a.yaml	Преобразование дампа ZX Spectrum > линейное адресное пространство
	zx_filter_b.yaml	Преобразование дампа ZX Spectrum > Фрагментация ячеек
	cl_filter_a.yaml	Преобразование дампа SDRAM_32 (2x16) > линейное адресное пространство
	cl_filter_b.yaml	Преобразование дампа SDRAM_32 (2x16) > Фрагментация ячеек


##### Обратная трансформация ( для проверки целостности )

	zx_filter_ar.yaml	Обратное преобразование в дамп ZX Spectrum
	zx_filter_br.yaml	Обратное преобразование в дамп ZX Spectrum
	cl_filter_ar.yaml	Обратное преобразование в дамп SDRAM_32 ( 2x16 )
	cl_filter_br.yaml	Обратное преобразование в дамп SDRAM_32 ( 2x16 )


---
Transformation array configuration example ( YAML file format )

Example:

``` YAML

counter:
  init: 0
  step: 1
  volume: 192
  unit_size: 32

transform:
  src:
    - format: 2
      scaler: 2048
    - format: 3
      scaler: 32
    - format: 3
      scaler: 256

  dst:
    - format: 8
      scaler: 32

```


---

<br>

##### Папка *results* результатов  

example1 - example8 : compressed files  

<br>

##### Папка 'check' - проверка обратной трансформации ( MD5 )

| Базовый файл (размер)     | Вариант A (ar)                          | Вариант B (br)                          | Основной файл (scr/bin)                 |
|---------------------------|-----------------------------------------|-----------------------------------------|-----------------------------------------|
| example1.scr (6912)       | 4a9db57bd34af7c7464918f555b84c1a        | 4a9db57bd34af7c7464918f555b84c1a        | 4a9db57bd34af7c7464918f555b84c1a        |
| example2.scr (6912)       | 7f0979997837b47b5c2dcb48cf9f8d0b        | 7f0979997837b47b5c2dcb48cf9f8d0b        | 7f0979997837b47b5c2dcb48cf9f8d0b        |
| example3.scr (6912)       | 36a03fc3dc2ed1c1109171db06fcfd23        | 36a03fc3dc2ed1c1109171db06fcfd23        | 36a03fc3dc2ed1c1109171db06fcfd23        |
| example4.scr (6912)       | b47bc2e1835a88154ea2d189f4161bd6        | b47bc2e1835a88154ea2d189f4161bd6        | b47bc2e1835a88154ea2d189f4161bd6        |
| example5.scr (6912)       | 3d281b5830f931f5d4d199a048471fe5        | 3d281b5830f931f5d4d199a048471fe5        | 3d281b5830f931f5d4d199a048471fe5        |
| example6.scr (6912)       | 9dd68048dc15525af9acfa6883398ddb        | 9dd68048dc15525af9acfa6883398ddb        | 9dd68048dc15525af9acfa6883398ddb        |
| example7.bin (16384)      | 66d2c7887b401109f466de65cf83c4f5        | 66d2c7887b401109f466de65cf83c4f5        | 66d2c7887b401109f466de65cf83c4f5        |
| example8.bin (16384)      | dca17a92e634a3c93a458f37ea6629bb        | dca17a92e634a3c93a458f37ea6629bb        | dca17a92e634a3c93a458f37ea6629bb        |

Все трансформации обратимы !

---

## Notes

- Original `.scr` files are ZX Spectrum screen dumps (6912 bytes).
- `.bin` files are larger synthetic or processed datasets (16384 bytes).

---

## Observations (brief)

- **LZMA / XZ** consistently provide the best compression ratio.
- **7z** is close to LZMA but slightly worse in most `.scr` cases.
- **RAR** shows stable but not leading performance.
- **GZ / ZIP / ARJ** are noticeably weaker for these datasets.
- **BZ2** performs worst on highly structured screen data.


---

### Compression Benchmark Trixs

https://trixs.sk/8bit-computer/ 

examples_trix folder content : 


> Values represent: **original → transformed → fragmented**


| Файл (6912)| 7z (О / A / B)       | arj (О / A / B)      | bz2 (О / A / B)      | gz (О / A / B)       | lzma (О / A / B)     | rar (О / A / B)      | xz (О / A / B)       | zip (О / A / B)      |
|------------|----------------------|----------------------|----------------------|----------------------|----------------------|----------------------|----------------------|----------------------|
| trix1.scr  | 4394 / 4228 / 3971   | 4706 / 4629 / 4170   | 5190 / 5178 / 4504   | 4597 / 4505 / 4058   | 4228 / 4096 / 3847   | 4617 / 4519 / 4081   | 4276 / 4144 / 3892   | 4737 / 4646 / 4199   |
| trix2.scr  | 4226 / 4152 / 3768   | 4284 / 4262 / 3901   | 4545 / 4551 / 4113   | 4174 / 4146 / 3794   | 4131 / 4019 / 3652   | 4308 / 4271 / 3840   | 4176 / 4064 / 3700   | 4314 / 4287 / 3935   |
| trix3.scr  | 2453 / 2411 / 2548   | 2556 / 2532 / 2649   | 2996 / 2968 / 2779   | 2451 / 2426 / 2529   | 2366 / 2302 / 2428   | 2512 / 2462 / 2599   | 2412 / 2348 / 2476   | 2591 / 2567 / 2670   |
| trix4.scr  | 4931 / 4853 / 4480   | 5107 / 5057 / 4641   | 5739 / 5750 / 5039   | 5009 / 5152 / 4759   | 4809 / 4745 / 4365   | 5126 / 5065 / 4659   | 4856 / 4792 / 4412   | 5149 / 5092 / 4674   |
| trix5.scr  | 2274 / 2220 / 2016   | 2571 / 2487 / 2152   | 2818 / 2791 / 2310   | 2450 / 2360 / 2040   | 2174 / 2106 / 1898   | 2452 / 2353 / 2082   | 2220 / 2152 / 1944   | 2590 / 2501 / 2181   |
| trix6.scr  | 5250 / 5213 / 4882   | 5300 / 5263 / 5052   | 5828 / 5845 / 5327   | 5194 / 5160 / 4943   | 5147 / 5090 / 4764   | 5360 / 5306 / 5061   | 5192 / 5136 / 4812   | 5334 / 5301 / 5084   |
| trix7.scr  | 4137 / 4019 / 3647   | 4351 / 4297 / 3871   | 4641 / 4651 / 3921   | 4244 / 4175 / 3759   | 3995 / 3882 / 3543   | 4335 / 4250 / 3773   | 4040 / 3928 / 3588   | 4384 / 4316 / 3900   |
| trix8.scr  | 3754 / 3668 / 3238   | 3973 / 3885 / 3417   | 4255 / 4249 / 3526   | 3866 / 3778 / 3299   | 3627 / 3542 / 3113   | 3860 / 3797 / 3345   | 3672 / 3588 / 3160   | 4006 / 3919 / 3440   |
| trix9.scr  | 4618 / 4495 / 4106   | 4678 / 4665 / 4262   | 5021 / 5043 / 4313   | 4559 / 4547 / 4147   | 4476 / 4355 / 4004   | 4717 / 4645 / 4169   | 4524 / 4400 / 4048   | 4699 / 4688 / 4288   |
| trix10.scr | 3783 / 3744 / 3415   | 4040 / 3981 / 3567   | 4318 / 4331 / 3658   | 3930 / 3867 / 3440   | 3663 / 3618 / 3308   | 3959 / 3858 / 3469   | 3708 / 3664 / 3352   | 4071 / 4009 / 3582   |
| trix11.scr | 4201 / 4079 / 3792   | 4460 / 4359 / 3973   | 4914 / 4890 / 4218   | 4353 / 4244 / 3864   | 4055 / 3938 / 3674   | 4439 / 4294 / 3897   | 4100 / 3984 / 3720   | 4494 / 4386 / 4006   |
| trix12.scr | 5221 / 5038 / 4670   | 5306 / 5266 / 4856   | 5739 / 5750 / 5039   | 5199 / 5152 / 4759   | 4983 / 4875 / 4547   | 5333 / 5241 / 4870   | 5028 / 4920 / 4592   | 5340 / 5294 / 4901   |
| trix13.scr | 4066 / 4036 / 3632   | 4273 / 4230 / 3792   | 4689 / 4682 / 3935   | 4151 / 4112 / 3675   | 3966 / 3895 / 3519   | 4294 / 4132 / 3712   | 4012 / 3940 / 3564   | 4292 / 4254 / 3817   |
| trix14.scr | 4828 / 4756 / 4487   | 5040 / 5006 / 4618   | 5480 / 5516 / 4762   | 4937 / 4899 / 4511   | 4721 / 4667 / 4366   | 5097 / 5026 / 4638   | 4768 / 4712 / 4412   | 5078 / 5041 / 4653   |
| trix15.scr | 4076 / 3981 / 3699   | 4407 / 4323 / 3877   | 4798 / 4805 / 4082   | 4302 / 4207 / 3767   | 3977 / 3834 / 3590   | 4350 / 4147 / 3784   | 4024 / 3880 / 3636   | 4443 / 4349 / 3909   |
| trix16.scr | 5003 / 4866 / 4638   | 5177 / 5114 / 4770   | 5680 / 5675 / 5123   | 5065 / 5008 / 4657   | 4861 / 4742 / 4517   | 5188 / 5083 / 4782   | 4908 / 4788 / 4564   | 5206 / 5150 / 4799   |
| trix17.scr | 5551 / 5415 / 5160   | 5682 / 5672 / 5344   | 6250 / 6231 / 5562   | 5577 / 5559 / 5242   | 5423 / 5301 / 5038   | 5716 / 5680 / 5362   | 5468 / 5348 / 5084   | 5718 / 5701 / 5384   |
| trix18.scr | 4137 / 4096 / 3836   | 4279 / 4234 / 3989   | 4722 / 4721 / 4183   | 4165 / 4125 / 3870   | 4028 / 3987 / 3718   | 4287 / 4133 / 3920   | 4076 / 4032 / 3764   | 4306 / 4267 / 4012   |
| trix19.scr | 3345 / 3275 / 3048   | 3450 / 3408 / 3179   | 3686 / 3686 / 3455   | 3326 / 3293 / 3061   | 3233 / 3171 / 2924   | 3389 / 3331 / 3108   | 3280 / 3216 / 2972   | 3467 / 3435 / 3203   |
| trix20.scr | 4487 / 4394 / 3974   | 4674 / 4614 / 4152   | 5039 / 5028 / 4250   | 4567 / 4502 / 4036   | 4328 / 4229 / 3870   | 4694 / 4625 / 4095   | 4376 / 4276 / 3916   | 4708 / 4644 / 4178   |
| trix21.scr | 4096 / 4052 / 3697   | 4215 / 4147 / 3892   | 4646 / 4600 / 4226   | 4102 / 4038 / 3763   | 3973 / 3901 / 3558   | 4265 / 4096 / 3819   | 4020 / 3948 / 3604   | 4243 / 4180 / 3905   |
| trix22.scr | 4749 / 4667 / 4323   | 4873 / 4826 / 4463   | 5312 / 5295 / 4695   | 4767 / 4711 / 4353   | 4606 / 4543 / 4205   | 4904 / 4835 / 4498   | 4652 / 4588 / 4252   | 4908 / 4853 / 4495   |
| trix23.scr | 3990 / 3909 / 3384   | 4289 / 4276 / 3579   | 4782 / 4789 / 3734   | 4175 / 4162 / 3446   | 3840 / 3796 / 3267   | 4290 / 4156 / 3519   | 3888 / 3840 / 3312   | 4316 / 4304 / 3588   |
| trix24.scr | 4971 / 4824 / 4514   | 5088 / 5056 / 4695   | 5693 / 5703 / 4940   | 4988 / 4943 / 4581   | 4845 / 4720 / 4383   | 5160 / 5098 / 4731   | 4892 / 4764 / 4428   | 5129 / 5085 / 4723   |
| trix25.scr | 4998 / 4882 / 4500   | 5133 / 5096 / 4641   | 5615 / 5615 / 4806   | 5026 / 4972 / 4525   | 4866 / 4738 / 4381   | 5167 / 5080 / 4649   | 4912 / 4784 / 4428   | 5167 / 5114 / 4667   |
| trix26.scr | 3505 / 3430 / 3267   | 3681 / 3624 / 3438   | 4054 / 4037 / 3709   | 3557 / 3504 / 3294   | 3388 / 3325 / 3148   | 3582 / 3516 / 3352   | 3436 / 3372 / 3192   | 3698 / 3646 / 3436   |
| trix27.scr | 2931 / 2857 / 2666   | 3171 / 3080 / 2792   | 3467 / 3463 / 2920   | 3050 / 2957 / 2668   | 2818 / 2733 / 2554   | 3014 / 2950 / 2726   | 2864 / 2780 / 2600   | 3191 / 3099 / 2810   |
| trix28.scr | 3540 / 3447 / 3139   | 3705 / 3643 / 3282   | 4016 / 4023 / 3478   | 3584 / 3522 / 3155   | 3420 / 3330 / 3024   | 3646 / 3570 / 3223   | 3468 / 3376 / 3072   | 3725 / 3664 / 3297   |
| trix29.scr | 4720 / 4642 / 4309   | 4791 / 4754 / 4432   | 5205 / 5217 / 4623   | 4686 / 4647 / 4320   | 4565 / 4484 / 4183   | 4846 / 4788 / 4451   | 4612 / 4532 / 4228   | 4827 / 4789 / 4462   |
| trix30.scr | 4364 / 4303 / 3966   | 4688 / 4626 / 4161   | 5172 / 5154 / 4341   | 4570 / 4510 / 4045   | 4235 / 4189 / 3859   | 4658 / 4569 / 4070   | 4280 / 4236 / 3904   | 4711 / 4652 / 4187   |
| trix31.scr | 4449 / 4343 / 4125   | 4444 / 4416 / 4218   | 4880 / 4885 / 4494   | 4337 / 4305 / 4097   | 4276 / 4215 / 4001   | 4515 / 4467 / 4260   | 4324 / 4260 / 4048   | 4478 / 4447 / 4239   |
| trix32.scr | 4700 / 4588 / 4273   | 4836 / 4787 / 4385   | 5347 / 5358 / 4638   | 4732 / 4672 / 4275   | 4532 / 4467 / 4144   | 4890 / 4807 / 4418   | 4576 / 4512 / 4192   | 4873 / 4814 / 4417   |
| trix33.scr | 4119 / 4000 / 3719   | 4295 / 4237 / 3891   | 4672 / 4687 / 4141   | 4187 / 4122 / 3776   | 3974 / 3867 / 3603   | 4262 / 4110 / 3803   | 4020 / 3912 / 3648   | 4328 / 4264 / 3918   |
| trix34.scr | 3325 / 3263 / 3092   | 3518 / 3464 / 3209   | 3795 / 3779 / 3444   | 3406 / 3350 / 3086   | 3210 / 3142 / 2973   | 3432 / 3379 / 3149   | 3256 / 3188 / 3020   | 3547 / 3492 / 3228   |
| trix35.scr | 4009 / 3949 / 3621   | 4184 / 4116 / 3755   | 4570 / 4525 / 3943   | 4058 / 4006 / 3634   | 3871 / 3835 / 3510   | 4120 / 4036 / 3707   | 3916 / 3880 / 3556   | 4199 / 4148 / 3776   |
| trix36.scr | 4141 / 4063 / 3718   | 4128 / 4107 / 3832   | 4423 / 4437 / 4047   | 4015 / 3998 / 3710   | 4017 / 3942 / 3589   | 4116 / 4069 / 3773   | 4064 / 3988 / 3636   | 4156 / 4140 / 3852   |
| trix37.scr | 4294 / 4183 / 3768   | 4378 / 4347 / 3911   | 4698 / 4700 / 4014   | 4257 / 4236 / 3798   | 4149 / 4033 / 3650   | 4406 / 4340 / 3829   | 4196 / 4080 / 3696   | 4398 / 4378 / 3940   |


| New Name   | Original Name |
|------------|--------------|
| trix1.scr  | Trixs - Cannibal Island 2 (2022).scr |
| trix2.scr  | Trixs - Chase (2021).scr |
| trix3.scr  | Trixs - Conscience (2015).scr |
| trix4.scr  | Trixs - Desert dream (2023).scr |
| trix5.scr  | Trixs - Dizzzruptor (2012) (Forever XIII).scr |
| trix6.scr  | Trixs - Draco (2023).scr |
| trix7.scr  | Trixs - Eclipse (2009) (ArtField 2009, 2).scr |
| trix8.scr  | Trixs - Fantastic World (2012) (Forever XIII, 8).scr |
| trix9.scr  | Trixs - Fear (2008) (Forever 9, 3).scr |
| trix10.scr | Trixs - Forenext (2009) (FOReVER_neXt, 2).scr |
| trix11.scr | Trixs - Forest Escape (2023).scr |
| trix12.scr | Trixs - Freedom (2014) (Forever 2014 Olympic Edition, 4).scr |
| trix13.scr | Trixs - Future (2011) (DiHalt 2011, 3).scr |
| trix14.scr | Trixs - Gemba (2011).scr |
| trix15.scr | Trixs - Johnny the Ghost (2023).scr |
| trix16.scr | Trixs - Journey (2024).scr |
| trix17.scr | Trixs - Kral (2010) (DiHalt 2010, 2).scr |
| trix18.scr | Trixs - Kral 2 (2022).scr |
| trix19.scr | Trixs - Krivan (2021).scr |
| trix20.scr | Trixs - LAND (2010) (FOReVER 11, 2).scr |
| trix21.scr | Trixs - Land of freedom (2023).scr |
| trix22.scr | Trixs - My Jeep ZJ (2010) (ZX AAA Demo Compo 2010, 3).scr |
| trix23.scr | Trixs - My world (2014) (Chaos Constructions 2014, 4).scr |
| trix24.scr | Trixs - New Wave (2013).scr |
| trix25.scr | Trixs - Nomind (2014).scr |
| trix26.scr | Trixs - Oldman (2023).scr |
| trix27.scr | Trixs - Pixel (2009).scr |
| trix28.scr | Trixs - Racer (2019) (DiHalt Lite 2019, 2).scr |
| trix29.scr | Trixs - Spectrum light (2010) (ArtField 2010, 5).scr |
| trix30.scr | Trixs - Spiderman (2011) (FOReVER 12, 9).scr |
| trix31.scr | Trixs - Spiderman2 (2005) (Forever Hex, 3).scr |
| trix32.scr | Trixs - Spy (2020) (DiHalt Lite 2020, 1).scr |
| trix33.scr | Trixs - SRT22 (2022).scr |
| trix34.scr | Trixs - unknown (2015) (Forever 2015 Back to the Cyberspace).scr |
| trix35.scr | Trixs - Waiting for freedom (2023).scr |
| trix36.scr | Trixs - Way home (2023).scr |
| trix37.scr | Trixs - ZX Cyber (2009) (Raww.orgy 2009, 1).scr |

