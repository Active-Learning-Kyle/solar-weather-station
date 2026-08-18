# GitHub 搭建导览（中文）

这份文件解释本仓库为什么这样组织，以及它如何服务 ENGG2202。它也是未来给学生使用的 GitHub 入门材料。

## 1. GitHub 到底是什么？

Git 是一套“版本控制”方法：它把一组文件在某个时刻的状态保存为一次 **commit（提交）**。GitHub 是托管 Git 仓库并支持协作的网站。

可以用工程项目来类比：

| GitHub 概念 | 工程类比 | 作用 |
|---|---|---|
| Repository | 一整个项目档案柜 | 放代码、图纸、BOM、测试、文档和历史记录 |
| Commit | 一次有说明的设计快照 | 说明“改了什么、为什么改”并可追溯 |
| Branch | 平行的设计试验线 | 在不破坏主版本的情况下尝试修改 |
| Issue | 工程任务/问题单 | 记录待解决问题、负责人、讨论和完成标准 |
| Pull Request | 正式设计变更申请 | 把一个 branch 的修改拿来审查、讨论、合并 |
| Release | 对外发布的里程碑版本 | 例如 v0.1 原理验证、v1.0 可复现版本 |

## 2. 为什么不把 26 页 PDF 直接上传就结束？

PDF 是一个很好的时间点快照，但不适合持续协作。GitHub-native 的做法是：

- `README.md` 让第一次访问的人 30 秒内理解项目；
- `docs/` 保存深入、可链接、可逐步更新的工程推理；
- `bom/`、`tests/`、`hardware/` 等把证据放在对应位置；
- Git 历史记录项目怎样逐步成长，而不只是最后结果。

原 PDF 仍然重要，应该作为 baseline 放进 `docs/source-documents/`，但它不是唯一信息来源。

## 3. GitHub 首页上每个区域是什么？

- **Code**：浏览仓库文件；也是项目默认入口。
- **Issues**：管理工程问题和任务，不等于“项目出错了”才使用。
- **Pull requests**：审查和合并设计变更。
- **Actions**：自动执行检查，例如编译 firmware、检查链接或验证数据格式。
- **Projects**：把 Issues 排成 Backlog / In progress / Done 看板。
- **Wiki**：额外知识库；本项目初期不启用，避免和 `docs/` 重复。
- **Insights**：查看贡献、流量、依赖与项目活动。

## 4. 每个文件和文件夹为什么存在？

### `README.md`

仓库的 front door。只负责定位、核心价值、状态、架构、快速入口。不要塞进所有设计细节。

对应 ENGG2202：训练学生把复杂工程向不同受众清楚表达。

### `docs/project-journey/`

记录 Problem → Existing solutions → References → Requirements → Decisions → Budget → Prototype → Test → Reflection。

对应 ENGG2202：让学习重点从“最后做出一个东西”扩展到可审查的工程过程。

### `hardware/`、`mechanical/`、`firmware/`、`dashboard/`

按工程子系统保存 source files 与说明。目录边界能支持团队分工，但各组员仍需理解系统接口。

对应 ENGG2202：系统工程、跨学科接口和配置管理。

### `bom/`

BOM 是 Bill of Materials。除了名称和数量，还记录规格、预算、供应商、采购状态和替代料。

对应 ENGG2202：budget planning、procurement、design-for-cost，以及“买得到”也是设计约束。

### `tests/`

先写 acceptance criteria，再收集证据。测试不是项目最后才做的展示，而是需求是否实现的判断方法。

对应 ENGG2202：validation、failure learning 和 evidence-based engineering。

### `.github/`

GitHub 的协作配置目录。Issue template 让每个问题都有背景、完成标准、风险和证据；Pull Request template 让每次变更可审查。

对应 ENGG2202：团队协作、peer review 和工程变更控制。

### `THIRD_PARTY.md` 与 `LICENSES/`

前者记录参考和复用的外部成果，后者记录 licence 判断。开源不代表“网上看到的都可以复制”。

对应 ENGG2202：工程伦理、知识产权和负责任的 open-source practice。

### `AI_USE.md`

只记录重要 AI 使用、验证方法和最终人类判断。

对应 ENGG2202：AI literacy 与 engineering accountability。

### `CHANGELOG.md`

用人能读懂的方式总结版本之间的变化；commit 是细粒度历史，changelog 是里程碑摘要。

## 5. 这次仓库搭建的发布顺序

1. **隔离项目目录**：避免把其他课程或私人文件上传。
2. **建立文件结构**：先定义信息应该放在哪里。
3. **初始化 Git**：让这个目录开始拥有版本历史。
4. **检查 `git status`**：确认将被追踪的只有本项目文件。
5. **第一次 commit**：保存“v0.1 foundation”快照。
6. **创建 GitHub repository**：建立远端公开项目地址。
7. **push**：把本地 commit 同步到 GitHub。
8. **建立 Issues**：把尚未完成的工程工作公开、可追踪地排出来。
9. **后续用 branch + Pull Request**：每个较大的设计改变都经过说明与审查。

## 6. 与 ENGG2202 的整体对应

```text
Problem identification
        ↓
Solution landscape and reference learning
        ↓
Requirements and measurable success criteria
        ↓
Concept selection, architecture, budget and risk
        ↓
Prototype, subsystem tests and integration
        ↓
Validation, iteration and documented failure
        ↓
Open-source release and teach-forward reflection
```

GitHub 在这里不是交作业的网盘，而是贯穿这条学习路径的工程工作台。

## 7. 下一阶段应该怎样使用

- 每个 engineering mission 建一个 Issue；
- 重要修改使用独立 branch；
- Pull Request 中说明设计理由、验证结果和风险；
- 每次硬件版本改变时同步更新 BOM、接口和测试；
- 每个 release 都明确哪些已验证、哪些仍是 limitation；
- 失败数据保留并解释，它们是学习证据而不是需要隐藏的内容。

